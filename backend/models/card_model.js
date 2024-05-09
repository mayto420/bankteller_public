
const db = require('../dbtesti');
const bcrypt=require('bcryptjs');

const card = {
    getAllCard: (callback) => {
        let sql = "SELECT * FROM card";
        db.query(sql, callback);
    },
    addCard(newCard, callback){
        bcrypt.hash(newCard.pin,10,function(err,hashedPin){
            return db.query("INSERT INTO card VALUES(?,?,?)",[newCard.cardNumber,hashedPin,newCard.accountID],callback);
        });
    },
    updateCard(un,updateData, callback){
        bcrypt.hash(updateData.pin, 10,function(err,hashedPin){
            return db.query("UPDATE card SET accountID=?,pin=? WHERE cardNumber=?",[updateData.accountID, hashedPin, un],callback);
        });

    },
    getOneCard(un, callback){
        return db.query("SELECT * FROM card WHERE cardNumber=?",[un],callback);

    },
    deleteCard(un, callback){
        return db.query("DELETE FROM card WHERE cardNumber=?",[un],callback);
    },
    login(un, callback){
        return db.query("SELECT pin FROM card WHERE cardNumber=?",[un], callback);
}

}


module.exports = card;