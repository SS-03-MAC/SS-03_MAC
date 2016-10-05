﻿using System;
using System.Runtime.Serialization;

/// <summary>
/// Base abstract classfor MAC types. Each MAC type will inherit this class.
/// Children of this class are used as wrapper classes for data, such that
/// all data can be fund easily, and to make sure data is comparable,
// equitable, and serializable
/// </summary>
namespace MAC.Types {
    public abstract class BaseType : IComparable<BaseType>, IEquatable<BaseType>,
                                     ISerializable
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
        /// 
        /// </summary>
        /// <param name="info"></param>
        /// <param name="context"></param>
        public BaseType(SerializationInfo info, StreamingContext context) { }


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
        public abstract int CompareTo(BaseType other);

        /// <summary>
        /// function inherited from IEquitable
        /// </summary>
        /// <param name="other"></param>
        /// <returns></returns>
        public abstract bool Equals(BaseType other);

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
        public abstract string ToString();
    }
}
