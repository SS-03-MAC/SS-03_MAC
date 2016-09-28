using System;
using System.Runtime.Serialization;


 namespace MAC.Types.User {
     /// <summary>
     /// Stores and vaildates Phyiscal Address
     /// </summary>
     public class Address : BaseType {
        /// <summary>
        /// This will check for:
        /// Street, and Zip
        /// </summary>
        /// <returns></returns>
        public bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the address
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int Equals(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the address as a string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public void GetObjectData(SerializationInfo info, StreamingContext context) {
            throw new NotImplementedException();
        }
     }
 }