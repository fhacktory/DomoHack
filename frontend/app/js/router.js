define([ "backbone", "views/index", "views/list" ], function(Backbone, IndexView, ListView) {
	var AppRouter = Backbone.Router.extend({
		routes : {
			'list' : 'list',
			'*actions' : 'defaultAction',
		}
	});
	var initialize = function() {
		var router = new AppRouter();
		
		router.on('route:defaultAction', function() {
			new IndexView();
		});
		
		router.on('route:list', function() {
			new ListView();
		});
		
		Backbone.history.start();
	};
	return {
		initialize : initialize
	};
});