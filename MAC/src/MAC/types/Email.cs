using System;
using System.Runtime.Serialization;
using System.Net.Mail;

namespace MAC.Types.User
{
    /// <summary>
    /// Stores and vaildates 
    /// </summary>
    public class Email : BaseType<Email, string>
    {
        /// <summary>
        /// Data that is stored in the model represented in as string
        /// </summary>
        private string Data;

        /// <summary>
        ///  Create an email type with an email as a strign
        /// </summary>
        /// <param name="email">An email address</param>
        public Email(string email)
        {
            Data = email;
            DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        }

        /// <summary>
        /// Default constructor
        /// </summary>
        public Email()
        {

        }

        /// <summary>
        /// This will check the email address with .NET class
        /// MailAddress
        /// </summary>
        /// <returns>If the stored email is valid</returns>
        public override bool Validate()
        {
            if (string.IsNullOrWhiteSpace(Data))
            {
                return false;
            }
            try
            {
                MailAddress ma = new MailAddress(Data);
            }
            catch (FormatException)
            {
                return false;
            }
            return true;
        }

        /// <summary>
        /// Compare emails
        /// </summary> 
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(object other)
        {
            if (other is Email)
            {
                return Data.CompareTo(((Email)other).Data);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the email
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(object other)
        {
            return CompareTo(other) == 0;
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /// <summary>
        /// Should return the email as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Returns the email address as a string
        /// </summary>
        /// <returns>Email address as a string</returns>
        public override string ToString()
        {
            return Data;
        }

        /// <summary>
        /// Return that email stored as string
        /// </summary>
        public override string Value
        {
            get
            {
                return Data;
            }

            set
            {
                Data = value;
            }
        }

        /// <summary>
        /// Access to the RAW data return has a object
        /// </summary>
        /// <returns>Raw data as an object</returns>>
        public override object GetRawObject()
        {
            return Data as object;
        }

        public static explicit operator string(MAC.Types.User.Email s)
        {
            return s.Data;
        }

        public static explicit operator MAC.Types.User.Email(string s)
        {
            return new Email(s);
        }
    }
}