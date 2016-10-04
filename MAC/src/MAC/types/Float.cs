using System;
using System.Runtime.Serialization;


namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates Floats
    /// Stored as SQL type float
    /// </summary>
    public class Float : BaseType
    {
        private double Data;

        public Float(double input) {
            Data = input;
            DatabaseFieldType = DatabaseFieldTypes.float_t;
        }

        public Float(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            Data = (double)info.GetValue("Data", typeof(double));
            DatabaseFieldType = DatabaseFieldTypes.float_t;
        }
        /// <summary>
        /// This will check if is a float
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            return true;
        }

        /// <summary>
        /// Compare the float
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            if (other is Float)
                return (int)(this.Data - ((Float)other).Data);
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the float
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            try {
                return this.CompareTo(other) == 0;
            } catch(ArgumentException) {
                return false;
            }
        }

        /// <summary>
        /// Should return the float
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
                throw new ArgumentException("info");
            info.AddValue("Data", Data);
        }

        public double Value {
            get { return Data; }
            set { Data = value; }
        }
    }
}
