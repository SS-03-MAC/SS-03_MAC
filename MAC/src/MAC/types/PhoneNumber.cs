using System;
using System.Runtime.Serialization;

 namespace MAC.Types.User {
     public class PhoneNumber : BaseType {
        /// <summary>
        /// Validates format of the number 
        /// Possiblely based on country code (e.g +1 for US)
        /// Will stored as SQL date type varchar or char type
        /// </summary>
        /// <returns>If the phone number is valid</returns>
        public override bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the phone nnumbers
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Check equality of the phone nubmer
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int Equals(BaseType other) {
           throw new NotImplementedException();
        }

        /// <summary>
        ///  Full phone number as a string
        /// </summary>
        /// <returns></returns>
        public override void GetObjectData(SerializationInfo info, StreamingContext cont) {
            throw new NotImplementedException();
        }
     }
 }