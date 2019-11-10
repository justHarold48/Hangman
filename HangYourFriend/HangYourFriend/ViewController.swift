//
//  ViewController.swift
//  HangYourFriend
//
//  Created by Harold Hatch on 10/8/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

import UIKit
import Foundation

class ViewController: UIViewController, UITextFieldDelegate
{
    let DUPLICATE_L_ERROR : String = "Duplicate Letter"
    let BASE_FULL_ERROR : String = "Base Complete"
    let STAKE_FULL_ERROR : String = "Stake Complete"
    
    let HINT_STATE = 4
    
    @IBOutlet weak var stageView: UITextView!
    @IBOutlet weak var guessTextField: UITextField!
    @IBOutlet weak var logLabel: UILabel!
    @IBOutlet weak var guessButton: UIButton!
    @IBOutlet weak var timeLabel: UILabel!
    @IBOutlet weak var playAgainButton: UIButton!
    
    var timer : Timer?
    
    // TODO: create rounded corners
    @IBOutlet weak var hgImageHolder: UIView!
    
    let stageWrapper = StageWrapper()
    var strStage: UnsafePointer<Int8>!
    var GAME_STATE: Int = 1
    var timeLeft = 35
    
    /* Checks if the letter choosen by user is
     * is in word set in stage.
     */
    @IBAction func guessButton(_ sender: Any)
    {
        timeLeft = 36
        
        if(guessTextField.hasText)
        {
            if(strlen(guessTextField.text!) == 1)
            {
               do
               {
                    var correctGuess : Bool = false
                    let letter = guessTextField.text?.lowercased()
                
                    try stageWrapper.catchException
                    {
                        correctGuess = self.stageWrapper.makeGuess((letter?.utf8CString.first)!)
                    }
                
                    if  (correctGuess)
                    {
                        stageView.text = stageWrapper.getStage()
                        postMessage(color: UIColor.blue, message: "Your guess is in the Word!!")
                    }else
                    {
                        stageView.text = stageWrapper.getStage()
                        if(stageWrapper.getState() == HINT_STATE)
                        {
                            postMessage(color: UIColor.blue, message: HINT)
                        }
                        else
                        {
                            postMessage(color: UIColor.red, message: "Sorry your guess is not in the word")
                        }
                    }
                }catch
                {
                    print(error.localizedDescription)
                    
                    if(error.localizedDescription.contains(DUPLICATE_L_ERROR))
                    {
                        postMessage(color: UIColor.red, message: (DUPLICATE_L_ERROR + " TRY AGAIN"))
                    }else if (error.localizedDescription.contains(BASE_FULL_ERROR))
                    {
                        stageView.text = stageWrapper.getStage()
                        postMessage(color: UIColor.green, message: "Word Complete, YOU WIN!! :)")
                        guessButton.isEnabled = false
                        playAgainButton.isHidden = false
                        timer?.invalidate()
                        timeLabel.text = "0"
                    }else if (error.localizedDescription.contains(STAKE_FULL_ERROR))
                    {
                        stageView.text = stageWrapper.getCompleteStage()
                        stageView.textColor = UIColor.orange
                        postMessage(color: UIColor.orange, message: "You Lose!!! Better Luck Next Time :(")
                        guessButton.isEnabled = false
                        playAgainButton.isHidden = false
                        timer?.invalidate()
                        timeLabel.text = "0"
                    }

                }
            }else
            {
                postMessage(color: UIColor.red, message: "Too Many Characters!!")
            }
        }
        else
        {
            postMessage(color: UIColor.red, message: "Nothing Entered, Try Again!!")
        }
        
        guessTextField.resignFirstResponder()
    }
    
    override func viewDidLoad()
    {
        super.viewDidLoad()
        // Do any additional setup after loading the view, typically from a nib.
    }
    
    override func viewDidAppear(_ animated: Bool)
    {
        guessTextField.delegate = self
        playAgainButton.isHidden = true
        stageWrapper.initStage(GUESSWORD)
        stageView.text = stageWrapper.getStage()
        guessTextField.autocorrectionType = .no
        
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardWillShow), name: NSNotification.Name.UIKeyboardWillShow, object: nil)
        NotificationCenter.default.addObserver(self, selector: #selector(keyboardWillHide), name: NSNotification.Name.UIKeyboardWillHide, object: nil)
        
        timer = Timer.scheduledTimer(timeInterval: 1.0 , target: self, selector: #selector(timeout), userInfo: nil, repeats: true)
    }

    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        self.view.endEditing(true)
    }
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool
    {
        let maxLength = 1
        let currentString: NSString = textField.text! as NSString
        let newString: NSString =
            currentString.replacingCharacters(in: range, with: string) as NSString
        
        return newString.length <= maxLength
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool
    {
        // resign keyboard after enter is pressed
        textField.resignFirstResponder()
        // make guess when enter pressed
        guessButton(self)
        return true;
    }
    
    func postMessage(color: UIColor, message: String)
    {
        guessTextField.text = ""
        logLabel.text = message
        logLabel.textColor = color
    }
    
    @objc func keyboardWillShow(notification: NSNotification) {
        if let keyboardSize = (notification.userInfo?[UIKeyboardFrameEndUserInfoKey] as? NSValue)?.cgRectValue {
            if self.view.frame.origin.y == 0 {
                self.view.frame.origin.y -= keyboardSize.height
            }
        }
    }
    
    @objc func keyboardWillHide(notification: NSNotification) {
        if self.view.frame.origin.y != 0 {
            self.view.frame.origin.y = 0
        }
    }
    
    @objc func timeout()
    {
        timeLeft -= 1
        timeLabel.text = "\(timeLeft)"
        
        if timeLeft <= 0
        {
            do{
                try stageWrapper.catchException
                {
                    self.stageWrapper.nextStageState()
                }
            }catch
            {
                if (error.localizedDescription.contains(STAKE_FULL_ERROR))
                {
                    stageView.text = stageWrapper.getCompleteStage()
                    stageView.textColor = UIColor.orange
                    postMessage(color: UIColor.orange, message: "Better Luck Next Time :(")
                    guessButton.isEnabled = false
                    playAgainButton.isHidden = false
                    timer?.invalidate()
                    timeLeft = 0
                    return
                }
            }

            stageView.text = stageWrapper.getStage()
            
            if(stageWrapper.getState() == HINT_STATE)
            {
                postMessage(color: UIColor.blue, message: HINT)
            }
            else
            {
                postMessage(color: UIColor.red, message: "Times up!!! You Lost a Turns")
            }
            
            timeLeft = 35
        }
    }
}

