using System;

namespace MAC.Models.Attributes.Validations
{
    [AttributeUsage(AttributeTargets.Field|AttributeTargets.Property)]
    public class Length : BaseValidation
    {
        /// <summary>
        /// Minimim length
        /// </summary>
        public int Minimum;
        /// <summary>
        /// Maxiumim length
        /// </summary>
        public int Maximum;
    }
}
