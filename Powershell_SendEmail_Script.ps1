Param(
      [String]$Att,
      [String]$Subj,
      [String]$Body
      )

Function Send-Email
{
    Param(
            [Parameter(`
            Mandatory=$true)]
          [String]$To,
            [Parameter(`
            Mandatory=$true)]
          [String]$From,
            [Parameter(`
            Mandatory=$true)]
          [String]$Password,
            [Parameter(`
            Mandatory=$true)]
          [String]$Subject,
            [Parameter(`
            Mandatory=$true)]
          [String]$Body,
            [Parameter(`
            Mandatory=$true)]
          [String]$attachment
         )
    try
    {
        $Msg = New-Object System.Net.MailMessage($From, $To, $Subject, $Body)
        $Srv = "smtp.gmail.com"
        if($attachment -ne $null)
        {
            try
            {
                $Attachments = $attachment -split ("\:\:");

                ForEach($val in $Attachments)
                {
                    $attch = New-0bject System.Net.Mail.Attachment($val)
                    $Msg.Attachments.Add($attch)
                }
            }
            catch
            {
                exit 2;
            }
            $client = New-Object Net.Mail.Smtpclient($Srv, 587)
            $client.EnableSsl = $true
            $client.Credentials = New-Object System.Net.NetworkCredential($From.Split("@")[0], $Password);
            $client.Send($Msg)
            Remove-Variable -Name client
            Remove-Variable -Name Password
            exit 7;
        }  
    }
    catch
        {
            exit 3;
        }
}

try
{
    Send-Email
        -attachment $Att
        -To "Address of the recipient"
        -Body $Body
        -Subject $Subj
        -password "tralalala"
        -From "Address of the sender"
}
catch
{
    exit 4;
}