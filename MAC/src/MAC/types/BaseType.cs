using System;
using System.Runtime.Serialization;

namespace MAC.Types
{
    /// <summary>
    /// Base abstract class for MAC types. Each MAC type will inherit this class.
    /// Children of this class are used as wrapper classes for data, such that
    /// all data and methods can be easily, and to make sure data is comparable,
    /// equitable, and serializable
    ///
    /// Methods that requiure generics
    /// </summary>
    public abstract class BaseType<T,V> : BaseType
    {
        /// <summary>
        /// Stores what type of field in that database is need store the data
        /// </summary>
        public DatabaseFieldTypes DatabaseFieldType;

        /// <summary>
        /// Default constructor
        /// </summary>
        public BaseType() { }

        /// <summary>
        /// Contrustor 
        /// </summary>
        /// <param name="type">Contrustor</param>
        public BaseType(T type)
        {

        }

        /// <summary>
        /// Serialization constructor
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public BaseType(SerializationInfo info, StreamingContext context) { }

        /// <summary>
        /// The underlineing value that is stored
        /// </summary>
        public abstract V Value { get; set; }
    }

    /// <summary>
    /// Method on the base type that do not requiure generics
    /// </summary>
    public abstract class BaseType : IComparable, IEquatable<object>,
                                     ISerializable
    {
        /// <summary>
        /// function to validate data for the given object is in the correct format
        /// independantly inplemented by each child class
        /// </summary>
        /// <returns>true if the type if valid</returns>
        public abstract bool Validate();

        /// <summary>
        ///  function inherited from IComparable
        /// </summary>
        /// <param name="other">Type of compare</param>
        /// <returns></returns>
        public abstract int CompareTo(object other);

        /// <summary>
        /// function inherited from IEquitable
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public abstract override bool Equals(object other);

        public override int GetHashCode()
        {
            return base.GetHashCode();
        }

        /// <summary>
        /// function inherited from ISerializable
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public abstract void GetObjectData(SerializationInfo info, StreamingContext context);

        /// <summary>
        /// String respention of the string object
        /// </summary>
        /// <returns>A end-user safe represention of the type</returns>
        public abstract override string ToString();

        /// <summary>
        /// A hack to get the raw value of the object
        /// 
        /// This method needs to be abstract since each type needs to decide 
        /// on how it stores it's data
        /// </summary>
        /// <returns></returns>
        public abstract object GetRawObject();
    }
}
