using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models.Attributes.Validations
{
    /// <summary>
    /// Validate a given 
    /// </summary>
    [AttributeUsage(AttributeTargets.Field|AttributeTargets.Property)]
    public class Regex : BaseValidation
    {
        public string regex { get; set; }
        public Regex(string regex)
        {
            this.regex = regex;
        }
    }
}
