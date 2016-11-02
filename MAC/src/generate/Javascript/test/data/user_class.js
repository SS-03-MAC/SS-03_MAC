var User = function(name, uses, fields){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;
  this.id = 0
  this.createdAt = Date.getTime();
  this.updatedAt = Date.getTime();

};

User.get = function(id){
  xhr = new XMLHTTPRequest();
  xhr.onreadystatechenge = function() {
    if(xhr.readystate == 4){
      if(xhr.status == 200){
        var result = eval("("+xhr.responseTest+")");
        return result;
      } else{
        throw new Error(xhr.statusText);
      }
    }
  }

  xhr.open("GET", "/users/id", true);
  xhr.send(null);
}

User.getAll = function(){
  xhr = new XMLHTTPRequest();
  xhr.onreadystatechenge = function() {
    if(xhr.readystate == 4){
      if(xhr.status == 200){
        var result = eval("("+xhr.responseTest+")");
        return result;
      } else{
        throw new Error(xhr.statusText);
      }
    }
  }

  xhr.open("GET", "/users", true);
  xhr.send(null);
}
