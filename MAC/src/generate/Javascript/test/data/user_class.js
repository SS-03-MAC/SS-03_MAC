var User = function(Password, FullName, City){
  this.Password = Password;
  this.FullName = FullName;
  this.City = City;
  this.id = 0;
  this.CreatedAt = Date.getTime();
  this.UpdatedAt = Date.getTime();

  this.save = function(){
    var xhr = new XMLHttpRequest();
    if(id == 0){
      xhr.open("POST", "/users/", true);
    } else{
      xhr.open("POST", "/users/"+id);
    }

    xhr.setRequestHeader("Content-type", "application/x-www-form-urlencoded");

    xhr.onreadystatechange = function(){
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          alert(xhr.responseText);
        } else{
          throw new Error(xhr.statusText);
        }
      }
    };

    xhr.send(serialize(this));
  };

  this.delete = function(){
    if(id == 0){
      return; //never saved to database, don't have to do anything
    }

    var xhr = new XMLHttpRequest();
    xhr.onreadystatechange = function() {
      if(xhr.readyState == 4){
        if(xhr.status == 200){
          alert(xhr.responseText);
        } else{
          throw new Error(xhr.statusText);
        }
      }
    };

    xhr.open("DELETE", "/users/"+id, true);
    xhr.send(null);
  };
};

User.get = function(id){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var result = eval("("+xhr.responseText+")");
        return result;
      } else{
        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", "/users/"+id, true);
  xhr.send(null);
};

User.getAll = function(){
  var xhr = new XMLHttpRequest();
  xhr.onreadystatechange = function() {
    if(xhr.readyState == 4){
      if(xhr.status == 200){
        var result = eval("("+xhr.responseText+")");
        return result;
      } else{
        throw new Error(xhr.statusText);
      }
    }
  };

  xhr.open("GET", "/users.json", true);
  xhr.send(null);
};

serialize = function(obj){
  var str = [];
  for(var p in obj){
    if(obj.hasOwnProperty(p)) {
      str.push(encodeURIComponent(p) + "=" + encodeURIComponent(obj[p]));
    }
  }
  return str.join("&");
};
