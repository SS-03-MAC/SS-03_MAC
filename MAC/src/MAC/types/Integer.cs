using System;
using System.Runtime.Serialization;


 namespace MAC.Types {    
     /// <summary>
     /// Stores and vaildates Integers
     /// </summary>
     public class Integer : BaseType {
        private int Data;


        public Integer(int input) {
            Data = input;
        }

        public Integer(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            Data = (int)info.GetValue("Data", typeof(int));
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
        /// <param name="other"></param>
        /// <returns></returns>
        public override int CompareTo(BaseType other) {
            if(other is Integer) {
                return this.Data - ((Integer)(other)).Data;
            }
            throw new ArgumentException();
        }

        /// <summary>
        /// Checks equality of the interger
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public override bool Equals(BaseType other) {
            return this.CompareTo(other) == 0;
        }

        /// <summary>
        /// Should return the integer
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public override void GetObjectData(SerializationInfo info, StreamingContext context) {
            if (info == null)
                throw new ArgumentNullException("info");
            info.AddValue("Data", Data);
        }
     }
 }