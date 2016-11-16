using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace MAC.Models.Attributes.Validations
{
    public class MinLength : BaseValidation
    {
        /// <summary>
        /// Specifies the minimum length of collection/string data allowed in a property.
        /// </summary>
        public int Length { get; set; }

        /// <summary>
        /// Override of  <see cref="BaseValidation.IsValid(object)"/> 
        /// </summary>
        /// <param name="o">object to test</param>
        /// <returns>
        /// <c>false</c> If the given lenght is less than min length
        /// <c>true</c> If the given object is longer
        /// </returns>
        public override bool IsValid(object o)
        {
            var attr = new System.ComponentModel.DataAnnotations.MinLengthAttribute(Length);
            return attr.IsValid(o);
          
        }

        /// <summary>
        /// Checks if the valdations has a valid length
        /// </summary>
        /// <exception cref="InvalidOperationException">If length is zero or less</exception>
        private void CheckLenth()
        {
            if (Length <= 0)
            {
                throw new InvalidOperationException("Length must be > 0");
            }
        }
    }
}
