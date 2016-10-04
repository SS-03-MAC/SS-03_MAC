using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
     /// <summary>
     /// Stores and vaildates boolean
     /// Stored as SQL type bit
     /// </summary>
     public class Boolean : BaseType {
        private bool Data;

        /// <summary>
        /// Initializes a Boolean from bool type
        /// </summary>
        /// <param name="input">the bool to be stored</param>
        public Boolean(bool input) {
            DatabaseFieldType = DatabaseFieldTypes.bit;
            Data = input;
        }

        /// <summary>
        /// Initializes a Boolean from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Boolean(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            DatabaseFieldType = DatabaseFieldTypes.bit;
            Data = (bool)info.GetValue("Data", typeof(bool));
        }

        /// <summary>
        /// This will check if is truely a boolean
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            return true;
        }

        /// <summary>
        /// Compare booleans (note that false < true)
        /// </summary>
        /// <param name="other">The BaseType object to compare with</param>
        /// <returns>-1 if this is false and other is true, 0 if this==other,
        /// and 1 if this is true and other is false</returns>
        public override int CompareTo(BaseType other) {
            if(other is Boolean) {
                if (!this.Data && ((Boolean)other).Data) return -1;
                if (this.Data == ((Boolean)other).Data) return 0;
                else return -1;
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the booleans
        /// </summary>
        /// <param name="other">the BaseType object to check equality with</param>
        /// <returns>true if equal, otherwise false</returns>
        public override bool Equals(BaseType other) {
            try {
                return this.CompareTo(other) == 0;
            }
            catch (ArgumentException e) {
                return false;
            }
        }

        /// <summary>
        /// Serialize the boolean
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            info.AddValue("Data", Data);
        }

        public bool Value {
            get { return Data; }
            set { Data = value; }
        }
    }
 }