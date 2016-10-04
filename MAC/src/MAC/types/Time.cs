using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates times
     /// Stored as a SQL time
     /// eg 08/28/2016
     /// </summary>
     public class Time : BaseType {
        private TimeSpan Data;

        public Time(TimeSpan input) {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.time;
        }

        public Time(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            Data = (TimeSpan)info.GetValue("Data", typeof(TimeSpan));
        }

        /// <summary>
        /// This will check for:
        /// Will check if the time is format can interpered as a time
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
            if (other is Time)
                return this.Data.CompareTo(((Time)other).Data);
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
            } catch (ArgumentException) {
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

        public TimeSpan Value {
            get { return Data; }
            set { Data = value; }
        }
     }
 }