using System;
using System.Runtime.Serialization;

/*
 * Base abstract classfor MAC types. Each MAC type will inherit this class. 
 * Children of this class are used as wrapper classes for data, such that
 * all data can be fund easily, and to make sure data is comparable, 
 * equitable, and serializable
 */
public abstract class BaseType : IComparable<BaseType>, IEquitable<BaseType>,
                                 ISerializable
{
	public BaseType() { }

    //function to validate data for the given object is in the correct format
    //independantly inplemented by each child class
    public bool Validate();

    //function inherited from IComparable
    public int compareTo(BaseType other);

    //function inherited from IEquitable
    public int equals(BaseType other);

    //function inherited from ISerializable
    public void GetObjectData(SerializationInfo info, StreamingContext context);
}
