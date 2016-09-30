using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates strings
     /// Stored as a SQL nvarchar or varchar
     /// </summary>
     public class String : BaseType {
        /// <summary>
        /// This will check for:
        /// Length with if is specified.
        /// Not sure how yet
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the strings
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Checks equality of the strings
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Should return the string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            throw new NotImplementedException();
        }
     }
 }