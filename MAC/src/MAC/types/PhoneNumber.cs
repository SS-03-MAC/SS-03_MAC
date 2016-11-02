using System;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;

namespace MAC.Types.User
{
    public class PhoneNumber : BaseType<PhoneNumber, string>
    {
        public DatabaseFieldTypes DatabaseFieldType = DatabaseFieldTypes.nvarchar;

        private string Data;
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
        public PhoneNumber(string PhoneNumber)
        {
            Data = PhoneNumber;
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
        public override int CompareTo(object other)
        {
            if (other is PhoneNumber)
            {
                return Data.CompareTo(((String)other).Value);
            }
            throw new ArgumentException();
        }


        /// <summary>
        /// Check equality of the phone nubmer
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(object other)
        {
            try
            {
                return CompareTo(other) == 0;
            }
            catch (ArgumentException)
            {
                return false;
            }
        }

        /// <summary>
        ///  Full phone number as a string
        /// </summary>
        /// <returns></returns>
        public override void GetObjectData(SerializationInfo info, StreamingContext cont)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            info.AddValue("Data", Data);
        }

        /// <summary>
        /// Returns data stored as a string
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data;
        }

        /// <summary>
        /// Access to underlyling data type
        /// </summary>
        public override string Value
        {
            get { return Data; }
            set { Data = Value; }
        }
    }
}