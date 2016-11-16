using MAC.Types;
using System;

namespace MAC.Models.Attributes.Validations
{
    /// <summary>
    /// Set a min and/or max length
    /// </summary>
    public class MaxLength : BaseValidation
    {
        /// <summary>
        /// Maxiumim length
        /// </summary>
        public int Length { get; set; }

        /// <summary>
        /// Allow blank, only check length if there is content
        /// </summary>
        public bool AllowBlank { get; set; }

        public MaxLength(int length)
        {
            Length = length;
        }

        /// <summary>
        /// Override of <see cref="BaseValidation.IsValid(object)"/> 
        /// Underlineing check uses <see cref="System.ComponentModel.DataAnnotations.MaxLengthAttribute"/>.
        /// </summary>
        /// <param name="o">object to test</param>
        /// <returns>
        ///  <c>false</c> if the given value's length is too long
        ///  <c>true</c> if the given value's length is shorter or equal to the max length
        /// </returns>
        public override bool IsValid(BaseType o)
        {
            if (o == null)
            {
                return true;
            }
            var attr = new System.ComponentModel.DataAnnotations.MaxLengthAttribute(Length);
            return attr.IsValid(o.GetRawObject());
        }
    }
}
