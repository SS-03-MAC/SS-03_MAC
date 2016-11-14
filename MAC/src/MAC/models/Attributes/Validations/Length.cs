using System;

namespace MAC.Models.Attributes.Validations
{
    [AttributeUsage(AttributeTargets.Field|AttributeTargets.Property)]
    public class Length : Attribute
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
