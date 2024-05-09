const express = require('express');
const router = express.Router();
const transaction = require('../models/transaction_model');

router.get('/', (request, response) => {
    transaction.getAllTransaction((err, dbResult) => {
        if (err) {
            response.json(err);
        } else {
            response.json(dbResult);
        }
    })
});

router.get('/:id', function (request, response) {
    transaction.getOneTransaction(request.params.id, function (err, result) {
        if (err) {
            response.send(err);
        }
        else {
            response.json(result);
        }
    })
});


module.exports = router;