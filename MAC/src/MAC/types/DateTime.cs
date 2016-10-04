using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates times
     /// Stored as a SQL time
     /// eg 08/28/2016
     /// </summary>
     public class DateTime : BaseType {
        private System.DateTime Data;

        public DateTime(System.DateTime input) {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.datetime;
        }

        public DateTime(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            Data = (System.DateTime)info.GetValue("Data", typeof(System.DateTime));
            DatabaseFieldType = DatabaseFieldTypes.datetime;
        }

        /// <summary>
        /// This will check for:
        /// Will check if the time is format can interpered as a datetime
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            return true;
        }

        /// <summary>
        /// Compare the time
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            if (other is DateTime)
                return this.Data.CompareTo(((DateTime)other).Data);
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the time
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            try {
                return this.CompareTo(other) == 0;
            }
            catch (ArgumentException) {
                return false;
            }
        }

        /// <summary>
        /// Should return the string
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            info.AddValue("Data", Data);
        }

        public System.DateTime Value {
            get { return Data; }
            set { Data = value; }
        }
     }
 }