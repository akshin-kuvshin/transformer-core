// author: Danila "akshin_" Axyonov

using TransformerCore.Model;
using Teigha.Geometry;
using Teigha.DatabaseServices;
using HostMgd.ApplicationServices;

namespace TransformerCore.Builder
{
    /// <summary>
    /// Класс, реализующий создание сердечника трансформатора с заданными параметрами и добавление его в документ NanoCAD с помощью соответствующего API.
    /// </summary>
    public static class Builder
    {
        /// <summary>
        /// Метод, создающий и возвращающий объёмное тело сердечника трансформатора с заданными параметрами.
        /// </summary>
        /// <param name="parameters">Параметры сердечника трансформатора.</param>
        /// <returns>Экземпляр Solid3d, соответвующий объёмному телу сердечника транформатора.</returns>
        private static Solid3d CreateCore(TransformerCoreParameters parameters)
        {
            var coreBase = CreateCoreBase(parameters);

            var core = new Solid3d();
            core.Extrude(coreBase, parameters.TotalWidth, 0);

            return core;
        }

        /// <summary>
        /// Метод, создающий и возвращающий плоское основание сердечника трансформатора с заданными параметрами.
        /// </summary>
        /// <param name="parameters">Параметры сердечника трансформатора.</param>
        /// <returns>Экземпляр Region, соответсвующий плоскому основанию сердечника трансформатора.</returns>
        private static Region CreateCoreBase(TransformerCoreParameters parameters)
        {
            Point2d[] points = new Point2d[]
            {
                new Point2d(0, 0), // A
                new Point2d(0, parameters.TotalHeight - parameters.ToothHeight), // B
                new Point2d(0, parameters.TotalHeight), // C
                new Point2d(parameters.SideToothLength, parameters.TotalHeight), // D
                new Point2d(parameters.SideToothLength, parameters.TotalHeight - parameters.ToothHeight), // E
                new Point2d(parameters.SideToothLength + parameters.ToothStepLength, parameters.TotalHeight - parameters.ToothHeight), // F
                new Point2d(parameters.SideToothLength + parameters.ToothStepLength, parameters.TotalHeight), // G
                new Point2d(parameters.SideToothLength + parameters.ToothStepLength + parameters.MedianToothLength, parameters.TotalHeight), // H
                new Point2d(parameters.SideToothLength + parameters.ToothStepLength + parameters.MedianToothLength, parameters.TotalHeight - parameters.ToothHeight), // I
                new Point2d(parameters.SideToothLength + 2 * parameters.ToothStepLength + parameters.MedianToothLength, parameters.TotalHeight - parameters.ToothHeight), // J
                new Point2d(parameters.SideToothLength + 2 * parameters.ToothStepLength + parameters.MedianToothLength, parameters.TotalHeight), // K
                new Point2d(2 * parameters.SideToothLength + 2 * parameters.ToothStepLength + parameters.MedianToothLength, parameters.TotalHeight), // L
                new Point2d(2 * parameters.SideToothLength + 2 * parameters.ToothStepLength + parameters.MedianToothLength, parameters.TotalHeight - parameters.ToothHeight), // M
                new Point2d(2 * parameters.SideToothLength + 2 * parameters.ToothStepLength + parameters.MedianToothLength, 0) // N
            };

            var coreBaseContour = new Polyline();
            for (int i = 0; i < points.Length; ++i)
                coreBaseContour.AddVertexAt(i, points[i], 0, 0, 0);
            coreBaseContour.Closed = true;

            var curves = new DBObjectCollection();
            curves.Add(coreBaseContour);
            var regions = Region.CreateFromCurves(curves);
            var coreBase = regions[0] as Region;

            return coreBase;
        }

        /// <summary>
        /// Метод, реализующий создание сердечника трансформатора с заданными параметрами и добавление его в документ NanoCAD.
        /// </summary>
        /// <param name="parameters">Параметры сердечника трансформатора.</param>
        public static void Build(TransformerCoreParameters parameters)
        {
            var document = Application.DocumentManager.MdiActiveDocument;
            var database = document.Database;
            using (var transaction = database.TransactionManager.StartTransaction())
            {
                var blockTable = transaction.GetObject(database.BlockTableId, OpenMode.ForRead) as BlockTable;
                var blockTableRecords = transaction.TransactionManager.GetObject(blockTable[BlockTableRecord.ModelSpace], OpenMode.ForWrite) as BlockTableRecord;

                var core = CreateCore(parameters);

                blockTableRecords.AppendEntity(core);
                transaction.AddNewlyCreatedDBObject(core, true);
                transaction.Commit();
            }
        }
    }
}
