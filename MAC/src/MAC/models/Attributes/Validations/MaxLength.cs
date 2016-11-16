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
        /// </summary>
        /// <param name="o">object to test</param>
        /// <returns>
        ///  <c>false</c> if the given value's length is too long
        ///  <c>true</c> if the given value's length is shorter or equal to the max length
        /// </returns>
        public override bool IsValid(object o)
        {
            CheckLenth();

            // RequiredField is be used for null check
            if (o == null)
            {
                return true;
            }

            if (Length != 0 && o == null && AllowBlank)
            {
                return false;
            }

            string value = o as string;

            if (value != null && value.Length < 0)
            {
                return false;
            }

            return true;
        }

        /// <summary>
        /// Checks if the valdations has a valid length
        /// </summary>
        /// <exception cref="InvalidOperationException">If length is zero or less</exception>
        private void CheckLenth()
        {
            if (Length <= 0)
            {
              throw new  InvalidOperationException("Length must be > 0");
            }
        }
    }
}
