// author: Danila "akshin_" Axyonov

using TransformerCore;

namespace TransformerCore.View
{
    /// <summary>
    /// Класс формы, предназначенной для ввода и валидации (проверки) параметров сердечника трансформатора.
    /// </summary>
    public partial class MainForm : Form
    {
        /// <summary>
        /// Конструктор (по умолчанию), инициализирующий форму компонентами из Designer-а.
        /// </summary>
        public MainForm()
        {
            InitializeComponent();
        }

        /// <summary>
        /// Метод-хэндлер, ограничивающий ввод для TextBox-а символами, допустимыми для типа double (цифры 0-9, десятичный разделитель (запятая)).
        /// </summary>
        /// <param name="sender">Компонент, вызвавший событие. Подразумевается TextBox одного из шести вводимых параметров сердечника трансформатора.</param>
        /// <param name="e">Параметры события.</param>
        private void DoubleTypeTextBox_TextChanged(object sender, EventArgs e)
        {
            TextBox textBox = sender as TextBox;
            string old_text = textBox.Text;
            string new_text = Validator.CorrectDoubleTypeText(old_text);
            textBox.Text = new_text;

            // Текст не изменился => или был удалён символ, или добавлен допустимый символ =>
            // => "хорошее" изменение => если были сообщение об ошибке и красный цвет на кнопке, то убираем их.
            if (old_text.Equals(new_text))
            {
                textBox.BackColor = Color.White;
                ErrorMessageTextBox.Text = "";
                ValidationButton.BackColor = Color.White;
            }
        }

        /// <summary>
        /// Метод-хэндлер, запускающий процесс валидации (проверки) введённых параметров сердечника трансформатора.
        /// </summary>
        /// <param name="sender">Компонент, вызвавший событие. Подразумевается валидационная кнопка "Готово".</param>
        /// <param name="e">Параметры события</param>
        private void ValidationButton_Click(object sender, EventArgs e)
        {
            string totalHeightText = TotalHeightTextBox.Text,
                   totalWidthText = TotalWidthTextBox.Text,
                   medianToothLengthText = MedianToothLengthTextBox.Text,
                   sideToothLengthText = SideToothLengthTextBox.Text,
                   toothStepLengthText = ToothStepLengthTextBox.Text,
                   toothHeightText = ToothHeightTextBox.Text;

            double totalHeight,
                   totalWidth,
                   medianToothLength,
                   sideToothLength,
                   toothStepLength,
                   toothHeight;
            bool totalHeightParsingSuccess = double.TryParse(totalHeightText, out totalHeight);
            bool totalWidthParsingSuccess = double.TryParse(totalWidthText, out totalWidth);
            bool medianToothLengthParsingSuccess = double.TryParse(medianToothLengthText, out medianToothLength);
            bool sideToothLengthParsingSuccess = double.TryParse(sideToothLengthText, out sideToothLength);
            bool toothStepLengthParsingSuccess = double.TryParse(toothStepLengthText, out toothStepLength);
            bool toothHeightParsingSuccess = double.TryParse(toothHeightText, out toothHeight);
            bool parsingSuccess = totalHeightParsingSuccess && totalWidthParsingSuccess && medianToothLengthParsingSuccess && sideToothLengthParsingSuccess && toothStepLengthParsingSuccess && toothHeightParsingSuccess;
            if (!totalHeightParsingSuccess)
            {
                TotalHeightTextBox.BackColor = Color.Red;
            }
            if (!totalWidthParsingSuccess)
            {
                TotalWidthTextBox.BackColor = Color.Red;
            }
            if (!medianToothLengthParsingSuccess)
            {
                MedianToothLengthTextBox.BackColor = Color.Red;
            }
            if (!sideToothLengthParsingSuccess)
            {
                SideToothLengthTextBox.BackColor = Color.Red;
            }
            if (!toothStepLengthParsingSuccess)
            {
                ToothStepLengthTextBox.BackColor = Color.Red;
            }
            if (!toothHeightParsingSuccess)
            {
                ToothHeightTextBox.BackColor = Color.Red;
            }
            if (!parsingSuccess)
            {
                ErrorMessageTextBox.Text = "Неверный формат ввода.";
                ValidationButton.BackColor = Color.Red;
                return;
            }

            try
            {
                Model.TransformerCoreParameters parameters = new Model.TransformerCoreParameters(
                    totalHeight * 1e-3,
                    totalWidth * 1e-3,
                    medianToothLength * 1e-3,
                    sideToothLength * 1e-3,
                    toothStepLength * 1e-3,
                    toothHeight * 1e-3
                );
                ValidationButton.BackColor = Color.Green;

                Builder.Builder.Build(parameters);
                this.Close();
            }
            catch (Exception exception)
            {
                ErrorMessageTextBox.Text = exception.Message;
                ValidationButton.BackColor = Color.Red;
            }
        }
    }
}
