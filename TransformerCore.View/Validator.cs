// author: Danila "akshin_" Axyonov

namespace TransformerCore.View
{
    /// <summary>
    /// Валидатор вводимых в форму данных.
    /// </summary>
    public static class Validator
    {
        /// <summary>
        /// Корректировка строки, оставляющая в ней только символы, допустимые для типа double (цифры 0-9, десятичный разделитель (запятая)).
        /// </summary>
        /// <param name="value">Исходная строка.</param>
        /// <returns>Скорректированная строка</returns>
        public static string CorrectDoubleTypeText(string value)
        {
            const string allowedCharacters = ",0123456789";
            return new string(value.Where(character => allowedCharacters.Contains(character)).ToArray());
        }
    }
}
