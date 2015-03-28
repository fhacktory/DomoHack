define([ "backbone" ], 
function(Backbone) {
	var Widget = Backbone.Model.extend({
		defaults: {
			name: false,
			famille: false,
			type: false,
			unite: false,
		},
		validate: function(attributes){
		      if ( !attributes.name ){
		          return 'Every widget must have a name !!';
		      }
		  },
		work: function(){
			return this.get('name') + ' is working.';
		},
	});
	return Widget;
});

