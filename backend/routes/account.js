const express = require('express');
const router = express.Router();
const accounts = require('../models/account_model');

router.get('/', function(request, response) {
    accounts.getAllAccounts(function(err, result){
        if (err) {  
            response.json(err);
        } else {
            response.json(result);
        }
    });
});
router.get('/:id',function(request, response){
    accounts.getOneAccounts(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result[0]);
        }
    })
});

router.post('/',function(request, response){
    accounts.addAccounts(request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.put('/:id',function(request, response){
    accounts.updateAccounts(request.params.id, request.body, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    })
});

router.delete('/:id', function(request, response){
    accounts.deleteAccounts(request.params.id, function(err, result){
        if(err){
            response.send(err);
        }
        else {
            response.json(result.affectedRows);
        }
    });
});


module.exports = router;