using System;
using System.Runtime.Serialization;

/*
 * Base abstract classfor MAC types. Each MAC type will inherit this class.
 * Children of this class are used as wrapper classes for data, such that
 * all data can be fund easily, and to make sure data is comparable,
 * equitable, and serializable
 */

 namespace MAC.Types {
    public abstract class BaseType : IComparable<BaseType>, IEquitable<BaseType>,
                                     ISerializable
    {
        /// <summary>
        /// Stores what type of field in that database is need store the data
        /// </summary>
        public DatabaseFieldTypes DatabaseFieldType;
        
    	public BaseType() { }

        //function to validate data for the given object is in the correct format
        //independantly inplemented by each child class
        public bool Validate();

        //function inherited from IComparable
        public int CompareTo(BaseType other);

        //function inherited from IEquitable
        public int Equals(BaseType other);

        //function inherited from ISerializable
        public void GetObjectData(SerializationInfo info, StreamingContext context);
    }
}
