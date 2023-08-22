// Please see documentation at https://docs.microsoft.com/aspnet/core/client-side/bundling-and-minification
// for details on configuring this project to bundle and minify static web assets.

// Write your JavaScript code.

var uptimes = [];
var downtimes = [];


function reportTimes() {
    var reportString = "";
    for (var i = 0; i < times.length - 1; ++i) {
        reportString += (i + 1) + ": " + (uptimes[i + 1].timestamp - uptimes[i].timestamp) + " ";
    }
    return reportString; // add this somewhere or alert it
}

$(document).ready(function () {


    $('#typearea').keyup(function (evt) {

        if (evt.which != 16)  // ignore shift key
        {
            if (evt.which == 13) // detected carriage return key press
            {
                evt.preventDefault();

            }
            uptimes.push({
                "timestamp": evt.timeStamp,
                "keycode": evt.which
            });

            if (evt.which == 13) // Send lick event
            {
                $('#showResults').click();

            }

        }
        //alert('Time captured:' + times[times.length-1].timestamp);
    });

    $('#typearea').keydown(function (evt) {
        if (evt.which != 16) // ignore shift key
        {
            if (evt.which == 13) // detected carriage return key press
            {
                evt.preventDefault();
            }

            //if (evt.which == 13) alert('ENTER pressed!');
            downtimes.push({
                "timestamp": evt.timeStamp,
                "keycode": evt.which
            });
        }
        
        //alert('Time captured:' + times[times.length-1].timestamp);
    });

    $('#showResults').click(function (e) {

        // Get Verification Token value
        var token = $('input[name="__RequestVerificationToken"]').val();
        
        // validation on total array length
        if (uptimes.length != 11 && downtimes.length != 11)
        {
            //alert('uptime length is ' + uptimes.length.toString());
            var OutputResults = "<div class='alert alert-danger'>Validation Error: Wrong Entry Sequence of Pass Code.</div>";
            $('#results').html(OutputResults);

            e.preventDefault();
            return; 
        }

        $.ajax({
            type: "POST",
            url: "Auth?handler=MyResult",
            headers: {
                RequestVerificationToken: token
            },
            data: {
                "uptimes": uptimes,
                "downtimes": downtimes
            },
            dataType: 'text',
            async: false,
            success: function (data) {

                var result = JSON.parse(data)

                // Forming output
                var OutputResults = "<h5>Results</h5>"; 
                OutputResults = OutputResults + "<p>Identified Subject: <b>" + result.pred_class + "</b><br />";
                OutputResults = OutputResults + "Prediction Probability: <b>" + result.pred_prob + "</b</p>"; 

                $('#results').html(OutputResults);                       
                e.preventDefault();
                
            },
            error: function (response, status, err) {
                alert("Failure: " + response.responseText);
            }
        });

     
    });

  

});

