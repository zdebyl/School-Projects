$(document).ready (function() {
        $("#add-element").click (function() {
            $.post("/addelement",
                {
                    elementnumber: $("#number").val(),
                    elementcode: $("#code").val(),
                    elementname: $("#name").val(),
                    elementcolour1: $("#colour1").val(),
                    elementcolour2: $("#colour2").val(),
                    elementcolour3: $("#colour3").val(),
                    elementradius: $("#radius").val()
                },
                function( data )
                {
                    alert(data);
                }
            );
                

            } );

        $("#remove-element").click (function() {
            $.post("/removeelement",
                {
                    removeelementname: $("#removename").val()
                },
                function( data )
                {
                    alert(data);
                }
            );
            } );

         $("#display-molecule").click (function() {
            $.post("/displaymolecule",
                {
                    displaymolecule: $("#display").val()
                },
                function( data )
                {
                    $("#moleculedisplaypage").html(data);
                }
            );
            } );

        
        
        $("#moleculedisplaypage").on("click", "#rotation-buttonx", function() {
            $.post("/rotation",
                {
                    typerequest: "xrotation",
                    degree: $("#x").val(),
                    moleculename: $("#moleculename").val()
                },
                function( data )
                {
                    $("#moleculedisplaypage").html(data);
                }
            );
                

            } );

        $("#moleculedisplaypage").on("click", "#rotation-buttony", function() {
            $.post("/rotation",
                {
                    typerequest: "yrotation",
                    degree: $("#y").val(),
                    moleculename: $("#moleculename").val()
                },
                function( data )
                {
                    $("#moleculedisplaypage").html(data);
                }
            );
                

            } );

        $("#moleculedisplaypage").on("click", "#rotation-buttonz", function() {
            $.post("/rotation",
                {
                    typerequest: "zrotation",
                    degree: $("#z").val(),
                    moleculename: $("#moleculename").val()
                },
                function( data )
                {
                    $("#moleculedisplaypage").html(data);
                }
            );
                

            } );




        $("#view-molecules").click(function() {
            $.ajax({
                url: "/viewmolecules",
                method: "GET",
                success: function(data) {
                    content = data.replace(/\n/g, "<br>");

                    $("#all-molecules-data").html(content);
                },
                error: function() {
                    console.log("broken");
                },
            });
        });
    }
)