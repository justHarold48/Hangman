//
//  PlayerViewController.swift
//  HangYourFriend
//
//  Created by Harold Hatch on 10/13/18.
//  Copyright © 2018 Onekliclabs. All rights reserved.
//

import UIKit
import SwiftUI

var GUESSWORD : String = ""
var HINT : String = ""

class PlayerViewController: UIViewController, UITextFieldDelegate
{
    let MAX_TEXT_LENGTH = 35
    
    @IBOutlet weak var wordTextField: UITextField!
    @IBOutlet weak var hintTextField: UITextField!
    
    @IBAction func startAction(_ sender: Any)
    {
        if (wordTextField.hasText)
        {
            var trimmedText = hintTextField.text?.trimmingCharacters(in: .whitespacesAndNewlines)
            
            if(hintTextField.hasText)
            {
                if((hintTextField.text?.count)! > MAX_TEXT_LENGTH)
                {
                    hintTextField.textColor = UIColor.gray
                    hintTextField.text = "Hint too long (35 characters or less)"
                    return
                }
                HINT = "Hint: " + trimmedText!
            }else
            {
                HINT = "Hint: No Hint Given"
            }
            
            trimmedText = wordTextField.text?.trimmingCharacters(in: .whitespacesAndNewlines)
            GUESSWORD = trimmedText!.lowercased()
            
            let storyboard = UIStoryboard(name: "Main", bundle: nil)
            let viewController: UIViewController  = storyboard.instantiateViewController(withIdentifier: "ViewController") as! ViewController
            viewController.modalPresentationStyle = .fullScreen
            //self.dismiss(animated: true, completion: nil)
            show(viewController, sender: self)
        }
    }
     
    override func viewDidLoad()
    {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        self.modalPresentationStyle = .currentContext
         wordTextField.delegate = self
        hintTextField.addTarget(self, action: #selector(clickAction), for: .touchDown)
              
    }

    override func didReceiveMemoryWarning()
    {
        super.didReceiveMemoryWarning()
        // Dispose of any resources that can be recreated.
    }
    
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) 
    {
        self.view.endEditing(true)
    }
    
    @objc func clickAction(textField: UITextField)
    {
        hintTextField.text = ""
    }
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool
    {
        let maxLength = 10
        let currentString: NSString = textField.text! as NSString
        let newString: NSString =
            currentString.replacingCharacters(in: range, with: string) as NSString
        return newString.length <= maxLength
    }
    
    func textFieldShouldReturn(_ textField: UITextField) -> Bool
    {
        // resign keyboard after enter is pressed
        textField.resignFirstResponder()
        return true;
    }
}
