using System;

namespace MAC.Models.Attributes.Validations
{
    /// <summary>
    /// Validate a field usig a regex
    /// </summary>
    [AttributeUsage(AttributeTargets.Field|AttributeTargets.Property)]
    public class Regex : BaseValidation
    {
        /// <summary>
        /// Regex to check with
        /// Must a a valid .NET Regex
        /// </summary>
        public string regex { get; set; }
        public Regex(string regex)
        {
            if (regex == null)
            {
                throw new ArgumentException("Regex can't be null!");
            }
            this.regex = regex;
        }

        /// <summary>
        /// Override of <typeparamref name="BaseValidation"/>
        /// </summary>
        /// <param name="o"></param>
        /// <returns>
        /// <c>false</c> if o is null or doesn't match <paramref name="regex"/>
        /// <c>true</c> if o match's <paramref name="regex"/>
        /// </returns>
        public override bool IsValid(object o)
        {
           if (o == null) {
                return false;
            }

            string value = o as string;
            System.Text.RegularExpressions.Regex regexChecker = new System.Text.RegularExpressions.Regex(regex);
            return value != null && regexChecker.IsMatch(value);
        }
    }
}
