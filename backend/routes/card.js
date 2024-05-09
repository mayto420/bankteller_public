const express = require('express');
const router = express.Router();
const card = require('../models/card_model');

router.get('/', function(request, response) {
    card.getAllCard(function(err, result) {
        if (err) {
            response.send(err);
        } else {
            response.json(result);
        }
    });
});
router.get('/:cardn',function(request,response){
    card.getOneCard(request.params.cardn, function(err,result){
        if(err){
            response.send(err);
        }
        else{
            console.log(result);
            response.json(result[0]);
        }
    })
});
router.post('/',function(request, response){
    card.addCard(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            response.json(result.affectedRows);
        }
    });
});
router.put('/:cardn', function(request, response){
    card.updateCard(request.params.cardn, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});
router.delete('/:cardn',function(request, response){
    card.deleteCard(request.params.cardn, function(err, result){
        if(err){
            response.send(err);
        }
        else{
            //response.json(result);
            console.log(result.affectedRows);
            response.json(result.affectedRows);
        }
    });
});

module.exports = router;