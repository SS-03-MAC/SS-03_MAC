using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates Phyiscal Address
     /// </summary>
     public class Integer : BaseType {
        /// <summary>
        /// This will check for:
        /// - if is an intger
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the interger
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the interger
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the interger
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            throw new NotImplementedException();
        }
     }
 }