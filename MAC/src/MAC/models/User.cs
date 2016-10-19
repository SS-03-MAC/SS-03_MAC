using System;
using System.Collections;
using System.Collections.Generic;

/// <summary>
///   Screensketch: Matthew Burket
///   This is an example model class.
///   I have subbed out the methods that will created in this file by the automatic system.
/// </summary>
public class User : BaseModel {
  /// <summary>
  /// Database id
  /// </summary>
  public long? Id { get; }
  /// <summary>
  /// A basic string field
  /// </summary>
  /// <returns></returns>
  //[Required]
  public string Email { get; set; }
  /// <summary>
  /// On set will set PasswordDigest to the BCrypt Password
  /// </summary>
  public virtual string Password { get; set; }
  /// <summary>
  /// How the Password is stored in the database
  /// </summary>
  /// <returns></returns>
  public string PasswordDigest { get; set; }


}
