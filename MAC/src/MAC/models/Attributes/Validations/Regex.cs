using MAC.Types;
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
        public string Pattern { get; set; }

        /// <summary>
        ///  Setup the regex validation
        /// </summary>
        /// <param name="pattern">Regex to create</param>
        /// <exception cref="ArgumentException">Pattern is null</exception>
        public Regex(string pattern)
        {
            if (pattern == null)
            {
                throw new ArgumentException("Regex can't be null!");
            }
            Pattern = pattern;
        }

        /// <summary>
        /// Override of <typeparamref name="BaseValidation"/>
        /// </summary>
        /// <param name="o"></param>
        /// <returns>
        /// <c>false</c> if o is null or doesn't match <paramref name="regex"/>
        /// <c>true</c> if o match's <paramref name="regex"/>
        /// </returns>
        public override bool IsValid(BaseType o)
        {
            var attr = new System.ComponentModel.DataAnnotations.RegularExpressionAttribute(Pattern);
            return attr.IsValid(o.GetRawObject());
        }
    }
}
