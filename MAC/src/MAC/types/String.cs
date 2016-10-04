using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates strings
     /// Stored as a SQL nvarchar or varchar
     /// </summary>
     public class String : BaseType {
        private string Data;

        public String(string input) {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.nvarchar;
        }

        public String(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            Data = info.GetValue("Data", typeof(string));
            DatabaseFieldType = DatabaseFieldTypes.int_t;
        }
        /// <summary>
        /// This will check for:
        /// Length with if is specified.
        /// Not sure how yet
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            return true;
        }

        /// <summary>
        /// Compare the strings
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            if (other is String)
                return this.Data.CompareTo(((String)other).Data);
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the strings
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            try {
                return this.CompareTo(other) == 0;
            } catch(ArgumentException e) {
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

        public string Value {
            get { return Data; }
            set { Data = value; }
        }
     }
 }