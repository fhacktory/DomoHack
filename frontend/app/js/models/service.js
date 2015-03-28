define([ "backbone" ], 
function(Backbone) {
	var Service = Backbone.Model.extend({
	  defaults: {
		  type: false,
		  baseUrl: "http://localhost:5000/rest/"
	  },
	  work: function(){
	      return this.get('name') + ' is working.';
	  },
	  validate: function(attributes){
	      if ( !attributes.type ){
	          return 'Every service must have a type !!';
	      }
	  },
	  getData: function () {
		  return this.get('baseUrl') + this.get('type');
	  }
	});
	return Service;
});
