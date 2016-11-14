using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

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
