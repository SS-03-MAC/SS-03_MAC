using System;
using System.Runtime.Serialization;
using System.Text.RegularExpressions;

namespace MAC.Types.User {
     /// <summary>
     /// Stores and vaildates 
     /// </summary>
     public class Email : BaseType {
        private string Data;

        /// <summary>
        /// 
        /// </summary>
        /// <param name="email">An email address</param>
        public Email(string email)
        {
            Data = email;
        }


        /// <summary>
        /// This will check for:
        /// - Vaild email address (a simple regex will work here)
        /// Regex for email valdations was taken from http://emailregex.com/
        /// </summary>
        /// <returns>If the stored email is valid</returns>
        public override bool Validate() {
            Regex EmailRegex = new Regex("[a - z0 - 9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?");
            return EmailRegex.IsMatch(Data);
        }

        /// <summary>
        /// Compare emails
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            if (other is Email)
            {

            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the email
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the email as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            throw new NotImplementedException();
        }
     }
 }