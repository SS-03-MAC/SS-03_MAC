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
        public bool Validate();

        /// <summary>
        /// Compare emails
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(BaseType other);

        /// <summary>
        /// Checks equality of the email
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int Equals(BaseType other);

        /// <summary>
        /// Should return the email as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public void GetObjectData(SerializationInfo info, StreamingContext context);
     }
 }