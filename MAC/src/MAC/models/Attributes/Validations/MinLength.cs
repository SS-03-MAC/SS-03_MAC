using MAC.Types;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models.Attributes.Validations
{
    /// <summary>
    /// Checks if there is a min length meet
    /// </summary>
    public class MinLength : BaseValidation
    {
        /// <summary>
        /// Specifies the minimum length of collection/string data allowed in a property.
        /// </summary>
        public int Length { get; set; }

        public MinLength(int length)
        {
            Length = length;
        }

        /// <summary>
        /// Override of  <see cref="BaseValidation.IsValid(object)"/>
        /// Underlaying check uses <see cref="System.ComponentModel.DataAnnotations.MinLengthAttribute"/> 
        /// </summary>
        /// <param name="o">object to test</param>
        /// <returns>
        /// <c>false</c> If the given lenght is less than min length
        /// <c>true</c> If the given object is longer
        /// </returns>
        public override bool IsValid(BaseType o)
        {
            if (o == null)
            {
                return true;
            }
            var attr = new System.ComponentModel.DataAnnotations.MinLengthAttribute(Length);
            return attr.IsValid(o.GetRawObject());

        }
    }
}
