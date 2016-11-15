using System;
using System.Runtime.Serialization;


namespace MAC.Types
{
    /// <summary>
    /// Stores and vaildates Currency
    /// Stored as SQL type varchar
    /// </summary>
    public class Currency : BaseType<Currency, decimal>
    {
        /// <summary>
        /// Data that is stored in the type represented in as decimal
        /// </summary>
        private decimal Data;

        /// <summary>
        /// Constructs Currency from a decimal type
        /// For now, we will just stroe amount, not currency type
        /// </summary>
        /// <param name="input">the decimal to be stored</param>
        public Currency(decimal input)
        {
            DatabaseFieldType = DatabaseFieldTypes.money;
            Data = input;
        }

        /// <summary>
        /// Constructs Currency from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Currency(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
            {
                throw new ArgumentNullException("info");
            }
            DatabaseFieldType = DatabaseFieldTypes.money;
            Data = (decimal)info.GetValue("Data", typeof(decimal));
        }
        /// <summary>
        /// This will check for:
        /// - if is an decimal
        /// </summary>
        /// <returns></returns>
        public override bool Validate()
        {
            return true;
        }

        /// <summary>
        /// Compare the decimal
        /// </summary>
        /// <param name="other">the BaseType object to compare with</param>
        /// <returns> A positive number if this > other, 0 if this == other, 
        /// and a negative number if this < other.</returns>
        public override int CompareTo(object other)
        {
            if (other is Currency)
            {
                return (int)(Data - ((Currency)(other)).Data);
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the decimal
        /// </summary>
        /// <param name="other">the BaseType object to check equality with</param>
        /// <returns>true if equal. Otherwise, false</returns>
        public override bool Equals(object other)
        {
            try
            {
                return CompareTo(other) == 0;
            }
            catch (ArgumentException)
            {
                return false;
            }
        }

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /// <summary>
        /// Serializes the Currency
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context)
        {
            if (info == null)
                throw new ArgumentNullException("info");
            info.AddValue("Data", Data);
        }

        /// <summary>
        /// Direct access to the data stored
        /// </summary>
        public override decimal Value
        {
            get { return Data; }
            set { Data = value; }
        }

        /// <summary>
        /// Returns the currency
        /// </summary>
        /// <returns></returns>
        public override string ToString()
        {
            return Data.ToString();
        }

        /// <summary>
        /// Access to the RAW data return has a object
        /// </summary>
        /// <returns>Raw data as an object</returns>
        public override object GetRawObject()
        {
            return Data as object;
        }
    }
}
