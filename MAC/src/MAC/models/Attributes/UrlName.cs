using System;

namespace MAC.Models.Attributes
{
    /// <summary>
    /// This attribute tells what url the model will be at
    /// </summary>
    /// <example>
    /// Let's say you have a user model and want to be accessiable at /users/.
    /// You would do the following
    /// <code>
    ///     [UrlName("users")]
    ///     public class User {
    ///         // Body of user class
    ///     }
    /// </code>
    /// </example>
    [AttributeUsage(AttributeTargets.Class, AllowMultiple = false)]
    public class UrlName : Attribute
    {
        public string Url { get; }

        public UrlName(string url)
        {
            Url = url;
        }
    }
}
