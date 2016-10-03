using System;
using System.Runtime.Serialization;


 namespace MAC.Types {
    /// <summary>
    /// Stores and vaildates Integers
    /// </summary>
    public class Integer : BaseType {
        private int data;

        /// <summary>
        /// Constructs Integer from an int type
        /// </summary>
        /// <param name="input">the int to be stored</param>
        public Integer(int input) {
            data = input;
        }

        /// <summary>
        /// Constructs Integer from SerializationInfo
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public Integer(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            data = (int)info.GetValue("data", typeof(int));
        }
        /// <summary>
        /// This will check for:
        /// - if is an integer
        /// </summary>
        /// <returns></returns>
        public override bool Validate() {
            return true;
        }

        /// <summary>
        /// Compare the integer
        /// </summary>
        /// <param name="other">the BaseType object to compare with</param>
        /// <returns> A positive number if this > other, 0 if this == other, 
        /// and a negative number if this < other.</returns>
        public override int CompareTo(BaseType other) {
            if(other is Integer) {
                return this.data - ((Integer)(other)).data;
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the interger
        /// </summary>
        /// <param name="other">the BaseType object to check equality with</param>
        /// <returns>true if equal. Otherwise, false</returns>
        public override bool Equals(BaseType other) {
            try {
                return this.CompareTo(other) == 0;
            } catch (ArgumentException e){
                return false;
            }
        }

        /// <summary>
        /// Serializes the Integer
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            info.AddValue("data", data);
        }

        public int Value {
            get { return data; }
            set { data = value; }
        }
     }
 }