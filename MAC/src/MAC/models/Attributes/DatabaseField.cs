using System;

namespace MAC.Models.Attributes
{
    [AttributeUsage(AttributeTargets.Field | AttributeTargets.Property, AllowMultiple = false)]
    public class DatabaseField : Attribute
    {
        /// <summary>
        /// Name of the table
        /// </summary>
        public string Name { get; }

        /// <summary>
        /// Create attribute with a name
        /// </summary>
        /// <param name="name">Name of database field</param>
        public DatabaseField(string name)
        {
            Name = name;
        }
    }
}
