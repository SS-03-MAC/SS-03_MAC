using System;
using System.Runtime.Serialization;

public abstract class BaseType : IComparable, IEquitable<BaseType>, ISerializable
{
	public BaseType()
	{

	}

    public bool Validate();

    public int compareTo(Object other);

    public int equals(BaseType other);

    public void GetObjectData(SerializationInfo info, StreamingContext context);
}
