require.config({
	paths: {
		'jquery': 'libs/jquery',
		'underscore': 'libs/underscore',
		'backbone': 'libs/backbone',
		'service': 'models/service',
		'widget': 'models/widget'
	},
	shim: {
		'underscore': {
			exports: '_'
		},
		'backbone': {
			deps: ["underscore", "jquery"],
			exports: 'Backbone'
		}
	}
});

require(
	["app"],
	function(App) {
		App.initialize();
	}
);