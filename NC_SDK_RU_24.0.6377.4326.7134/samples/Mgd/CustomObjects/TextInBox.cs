//
// Копирайт (С) 2019, ООО «Нанософт разработка». Все права защищены.
// 
// Данное программное обеспечение, все исключительные права на него, его
// документация и сопроводительные материалы принадлежат ООО «Нанософт разработка».
// Данное программное обеспечение может использоваться при разработке и входить
// в состав разработанных программных продуктов при соблюдении условий
// использования, оговоренных в «Лицензионном договоре присоединения
// на использование программы для ЭВМ «Платформа nanoCAD»».
// 
// Данное программное обеспечение защищено в соответствии с законодательством
// Российской Федерации об интеллектуальной собственности и международными
// правовыми актами.
// 
// Используя данное программное обеспечение,  его документацию и
// сопроводительные материалы вы соглашаетесь с условиями использования,
// указанными выше. 
//

using System;
using System.Drawing;
using System.Windows.Forms;
using System.Collections.Generic;
using System.ComponentModel;
using Multicad;
using Multicad.AplicationServices;
using Multicad.Runtime;
using Multicad.DatabaseServices;
using Multicad.DataServices;
using Multicad.Geometry;
using Multicad.CustomObjectBase;


namespace Multicad.Samples
{
  [CustomEntity("1C925FA1-842B-49CD-924F-4ABF9717DB62", "TextInBox", "TextInBox Sample Entity")]
  public class TextInBox : McCustomBase, IMcSerializable
  {
    private Point3d _pnt1 = new Point3d(50, 50, 0);
    private Point3d _pnt2 = new Point3d(150, 100, 0);
    private String _text = "Text field";
    private double _textHeight;
    public TextInBox()
    {
      UpdateTextHeight();
    }
    private void UpdateTextHeight()
    {
      _textHeight = Math.Abs(_pnt2.Y - _pnt1.Y) * 0.8;
      if (Math.Abs(_pnt2.X - _pnt1.X) < (_textHeight * _text.Length / 1.32))
        _textHeight = Math.Abs(_pnt2.X - _pnt1.X) * 1.32 / _text.Length;
    }

    [DisplayName("Текстовая метка")]
    [Description("Описание метки")]
    [Category("Тестовый объект")]
    public String Text
    {
      get
      {
        return _text;
      }
      set
      {
        if (!TryModify()) return;//без этого не будет сохранятся Undo и перерисовыватся объект
        _text = value;
      }
    }
    
    public bool TryModify()
    {
      TryModify(0);
      return true;
    }
    
    public override void OnDraw(GeometryBuilder dc)
    {
      dc.Clear();
      dc.Color = McDbEntity.ByObject;//цвет будет братся из свойств объекта, и при изменении автоматически перерисуется
      dc.DrawPolyline(new Point3d[] { _pnt1, new Point3d(_pnt1.X, _pnt2.Y, 0), _pnt2, new Point3d(_pnt2.X, _pnt1.Y, 0), _pnt1 });
      dc.TextHeight = _textHeight;
      dc.Color = Color.Blue;//Текст рисуем синим цветом
      dc.DrawMText(new Point3d((_pnt2.X + _pnt1.X) / 2.0, (_pnt2.Y + _pnt1.Y) / 2.0, 0), Vector3d.XAxis, Text, HorizTextAlign.Center, VertTextAlign.Center);
    }

    public override hresult OnMcSerialization(McSerializationInfo info)
    {
      info.Add("_pnt1", _pnt1);
      info.Add("_pnt2", _pnt2);
      info.Add("_textHeight", _textHeight);
      info.Add("_text", _text);
      return hresult.s_Ok;
    }

    public override hresult OnMcDeserialization(McSerializationInfo info)
    {
      if (!info.GetValue("_pnt1", out _pnt1))
        return hresult.e_Fail;
      if (!info.GetValue("_pnt2", out _pnt2))
        return hresult.e_Fail;
      if (!info.GetValue("_textHeight", out _textHeight))
        return hresult.e_Fail;
      if (!info.GetValue("_text", out _text))
        return hresult.e_Fail;
      return hresult.s_Ok;
    }
    public override void OnTransform(Matrix3d tfm)
    {
      if (!TryModify()) return;
      _pnt1 = _pnt1.TransformBy(tfm);
      _pnt2 = _pnt2.TransformBy(tfm);
    }
    public override bool GetGripPoints(GripPointsInfo info)
    {
      // Добавляем одну ручку в левый нижний угол прямоугольника
      info.AppendGrip(new McSmartGrip<TextInBox>(_pnt1, (obj, grip, offset) => { obj.TryModify(); obj._pnt1 += offset; }));

      // Добавляем вторую ручку в правый верхний угол прямоугольника
      info.AppendGrip(new McSmartGrip<TextInBox>(_pnt2, (obj, grip, offset) => { obj.TryModify(); obj._pnt2 += offset; }));
      return true;
    }

    public override hresult PlaceObject(PlaceFlags lInsertType)
    {
      InputJig jig = new InputJig();
      InputResult res = jig.GetPoint("Select first point:");
      if (res.Result != InputResult.ResultCode.Normal)
        return hresult.e_Fail;
      _pnt1 = res.Point;
      DbEntity.AddToCurrentDocument();
      //Исключаем себя из привязки, что бы osnap точки не липли к самому себе
      jig.ExcludeObject(ID);
      //Мониторинг движения мышкой
      jig.MouseMove = (s, a) =>
      {
        TryModify();
        _pnt2 = a.Point;
        UpdateTextHeight();
        DbEntity.Update(); //Обновляем примитив на чертеже
        InputJig.PropertyInpector.UpdateProperties(); // Обновляем свойства примтива на панели свойств
      };

      res = jig.GetPoint("Select second point:");
      if (res.Result != InputResult.ResultCode.Normal)
      {
        DbEntity.Erase();
        return hresult.e_Fail;
      }
      _pnt2 = res.Point;
      UpdateTextHeight();
      return hresult.s_Ok;
    }
    public override hresult OnEdit(Point3d pnt, EditFlags lInsertType)
    {
      TextInBox_Form frm = new TextInBox_Form(_text);
      frm.ShowDialog();
      Text = frm.NewText;

      return hresult.s_Ok;
    }
  }
}
