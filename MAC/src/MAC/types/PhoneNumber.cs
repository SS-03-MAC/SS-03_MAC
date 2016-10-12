using System;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;

namespace MAC.Types.User
{
    public class PhoneNumber : String
    {
        public DatabaseFieldTypes DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        /// <summary>
        /// Validates format of the number 
        /// Possiblely based on country code (e.g +1 for US)
        /// Will stored as SQL date type nvarchar or char type
        /// Taken from
        /// http://blog.stevenlevithan.com/archives/validate-phone-number
        ///
        /// </summary>
        /// <returns>If the phone number is valid</returns>
        public override bool Validate()
        {
            Regex regexObj = new Regex(@"^\(?([0-9]{3})\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})$");

            if (regexObj.IsMatch(Data))
            {
                string formattedPhoneNumber = regexObj.Replace(Data, "($1) $2-$3");
                return true;
            }
            else
            {
                return false;
            }
        }

        /// <summary>
        /// Create a new phone number
        /// </summary>
        /// <param name="PhoneNumber">Phone number in E.164 Format as a string</param>
        public PhoneNumber(string PhoneNumber) : base(PhoneNumber)
        {

        }

        /// <summary>
        /// Create from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public PhoneNumber(SerializationInfo info, StreamingContext context) : base(info, context)
        {

        }

        /// <summary>
        /// Compare the phone nnumbers
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other)
        {
            return base.CompareTo(other);
        }

        /// <summary>
        /// Check equality of the phone nubmer
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other)
        {
            return base.Equals(other);
        }

        /// <summary>
        ///  Full phone number as a string
        /// </summary>
        /// <returns></returns>
        public override void GetObjectData(SerializationInfo info, StreamingContext cont)
        {
            base.GetObjectData(info, cont);
        }

        /// <summary>
        /// Returns data stored as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return base.ToString();
        }
    }
}