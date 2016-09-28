using System;
using System.Runtime.Serialization;


 namespace MAC.Types.User {
     /// <summary>
     /// Stores and vaildates 
     /// </summary>
     public class User : BaseType {
        /// <summary>
        /// This will check for:
        /// - Vaild email address (a simple regex will work here)
        /// - 
        /// </summary>
        /// <returns></returns>
        public bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare emails
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the email
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int Equals(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the email as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public void GetObjectData(SerializationInfo info, StreamingContext context) {
            throw new NotImplementedException();
        }
     }
 }