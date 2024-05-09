const express=require('express');
const router=express.Router();
const login=require('../models/login_model');
const bcrypt=require('bcryptjs');
const jwt=require('jsonwebtoken');
const dotenv=require('dotenv');
dotenv.config();

router.post('/',function(request, response){
    console.log("test1");
    if(request.body.cardNumber && request.body.pin){
        console.log("testi2");


        login.checkPin(request.body.cardNumber, request.body.pin, function(err,result){
            if(err){
                console.log("testi3");
                console.log(err.errno);
                response.json(err.errno);
            }
            else{
                if(result.length > 0){
                    console.log("testi4");
                    bcrypt.compare(request.body.pin, result[0].pin, function(err, compareResult){
                        if(compareResult){
                            console.log('Kirjautuminen ok');
                            const token = genToken({ cardNumber: request.body.cardNumber });
                            response.send(token);
//response.send(result[10].password);
                        }
                        else {
                            console.log("Väärä salasana");
                            response.send(false);
                        }
                    })
                }
                else {
                    console.log("tunnusta ei ole");
                    response.send(false);
                }

            }
        });
    }
    else {
        console.log("Tunnus tai salasana puuttuu")
        response.send(false);
    }
});

function genToken(value){
    dotenv.config();
    return jwt.sign(value, process.env.MY_TOKEN, {expiresIn: '200s'});
}

module.exports=router;
