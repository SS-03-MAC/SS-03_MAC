using System;
using System.Runtime.Serialization;

 namespace MAC.Types.User {
     public class PhoneNumber : BaseType {
        /// <summary>
        /// Validates format of the number 
        /// Possiblely based on country code (e.g +1 for US)
        /// </summary>
        /// <returns>If the phone number is valid</returns>
        public bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Check equality of the phone nubmer
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public int Equals(BaseType other) {
           throw new NotImplementedException();
        }

        /// <summary>
        ///  Full phone number
        /// </summary>
        /// <returns></returns>
        public void GetObjectData(SerializationInfo info, StreamingContext cont {
            throw new NotImplementedException();
        }
     }
 }