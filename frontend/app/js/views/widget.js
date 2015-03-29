define([ "backbone", "underscore", "widget", "models/widgetCollection" ],
function(Backbone, _, Widget, WidgetCollection) {
	var Widget = Backbone.View.extend({
		el : $("body"),
		initialize : function() {
			_.bindAll(this, 'render', 'addItem');
			
			this.widgetCollection = new WidgetCollection;
			this.dataRest = false;
			var that = this;
			this.widgetCollection.fetch({
		        complete: function (datas) {
		        	that.dataRest = datas;
		        	that.renderListe();
		        }
		    });
		},
		
		events: {
	      'click button#addWidget': 'addItem'
	    },
		
	    template: _.template($('#widgetCollectionTemplate').html()),

	    renderListe: function() {
	    	$('#select-content', this.el).html(this.template({ "widgets": this.dataRest.responseJSON}));
	    },
	    
	    addItem: function(){
	    	var selectValue = $('#select-content', this.el).find("select#connectedObject").val();
			if (selectValue == "") {
				alert('Choose an object');
				return false;
			}
			console.log(this.dataRest.responseJSON)
	        $('#content', this.el).append("test");
        }	
	    
	});
	return Widget;
});