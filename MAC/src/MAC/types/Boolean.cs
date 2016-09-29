using System;
using System.Runtime.Serialization;


 namespace MAC.Types.User {
     /// <summary>
     /// Stores and vaildates boolean
     /// Stored as SQL type bit or boolean
     /// </summary>
     public class Boolean : BaseType {
        /// <summary>
        /// This will check if is truely a boolean
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare booleans
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the booleans
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int Equals(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the value of the boolean
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            throw new NotImplementedException();
        }
     }
 }