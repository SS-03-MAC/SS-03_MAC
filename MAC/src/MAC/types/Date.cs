using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates dates
     /// Stored as a SQL date
     /// eg 08/28/2016
     /// </summary>
     public class Date : BaseType {
        /// <summary>
        /// This will check for:
        /// Will check if the date is format can interpered as a date
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Compare the Date
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